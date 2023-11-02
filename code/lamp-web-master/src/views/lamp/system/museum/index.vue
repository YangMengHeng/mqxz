<template>
  <div class="app-container">
    <!--    表格上方一行的有关功能-->
    <div class="filter-container">
      <!--      搜索 摄像头ID栏-->
      <el-input
          v-model="queryParams.model.camId"
          :placeholder="$t('table.camera.camId')"
          class="filter-item search-item"
      />
      <!--      搜索 摄像头名称栏-->
      <el-input
          v-model="queryParams.model.camName"
          :placeholder="$t('table.camera.camName')"
          class="filter-item search-item"
      />
      <!--      搜索 摄像头X坐标栏-->
      <el-input
          v-model="queryParams.model.camPosX"
          :placeholder="$t('table.camera.camPosX')"
          class="filter-item search-item"
      />
      <!--      搜索 摄像头Y坐标栏-->
      <el-input
          v-model="queryParams.model.camPosY"
          :placeholder="$t('table.camera.camPosY')"
          class="filter-item search-item"
      />
      <!--      搜索 摄像头状态栏-->
      <el-input
          v-model="queryParams.model.camStatus"
          :placeholder="$t('table.camera.camStatus')"
          class="filter-item search-item"
      />


      <!--搜索 按钮-->
      <el-button
          class="filter-item"
          plain
          type="primary"
          @click="search"
      >
        {{ $t("table.search") }}
      </el-button>

      <!--添加摄像头 按钮-->
      <el-button
          class="filter-item"
          plain
          type="danger"
          @click="add"
      >
        {{ $t("table.camera.add") }}
      </el-button>

    </div>

    <!--表格-->
    <el-table
        :key="tableKey"
        ref="table"
        v-loading="loading"
        :data="tableData.records"
        border
        fit
        row-key="id"
        style="width: 100%;"
        @filter-change="filterChange"
        @selection-change="onSelectChange"
        @sort-change="sortChange"
        @cell-click="cellClick"
    >
      <!--      表头 全选框-->
      <el-table-column
          align="center"
          type="selection"
          width="40px"
          :reserve-selection="true"
      />
      <!--      表列 摄像头ID-->
      <el-table-column
          :label="$t('table.camera.camId')"
          :show-overflow-tooltip="true"
          align="center"
          prop="camId"
          width=""
      >
        <template slot-scope="scope">
          <span>{{ scope.row.id }}</span>
        </template>
      </el-table-column>
      <!--      表列 摄像头名称-->
      <el-table-column
          :label="$t('table.camera.camName')"
          :show-overflow-tooltip="true"
          align="center"
          prop="camName"
          width=""
      >
        <template slot-scope="scope">
          <span>{{ scope.row.camName }}</span>
        </template>
      </el-table-column>
      <!--      表列 摄像头X坐标-->
      <el-table-column
          :label="$t('table.camera.camPosX')"
          :show-overflow-tooltip="true"
          align="center"
          prop="camPosX"
          width=""
      >
        <template slot-scope="scope">
          <span>{{ scope.row.camPosX }}</span>
        </template>
      </el-table-column>
      <!--      表列 摄像头Y坐标-->
      <el-table-column
          :label="$t('table.camera.camPosY')"
          :show-overflow-tooltip="true"
          align="center"
          prop="camPosY"
          width=""
      >
        <template slot-scope="scope">
          <span>{{ scope.row.camPosY }}</span>
        </template>
      </el-table-column>
      <!--      表列 摄像头状态-->
      <el-table-column
          :label="$t('table.camera.camStatus')"
          :show-overflow-tooltip="true"
          align="center"
          prop="camStatus"
          width=""
      >
        <template slot-scope="scope">
          <span>{{ scope.row.camStatus }}</span>
        </template>
      </el-table-column>

      <!--单行的操作按钮-->
      <el-table-column
          :label="$t('table.operation')"
          column-key="operation"
          align="center"
          class-name="small-padding fixed-width"
          width="100px"
      >
        <template slot-scope="{ row }">
          <!--          <i-->
          <!--            class="el-icon-copy-document table-operation"-->
          <!--            :title="$t('common.delete')"-->
          <!--            style="color: #2db7f5;"-->
          <!--            @click="copy(row)"-->
          <!--          />-->
          <i
              class="el-icon-edit table-operation"
              :title="$t('table.camera.edit')"
              style="color: #2db7f5;"
              @click="edit(row)"
          />
          <i
              class="el-icon-delete table-operation"
              :title="$t('table.camera.delete')"
              style="color: #f50;"
              @click="singleDelete(row)"
          />
        </template>
      </el-table-column>
    </el-table>

    <!--表格页数设置-->
    <pagination
        v-show="tableData.total > 0"
        :limit.sync="queryParams.size"
        :page.sync="queryParams.current"
        :total="Number(tableData.total)"
        @pagination="fetch"
    />

    <!--添加界面-->
    <encState-edit
        ref="edit"
        :dialog-visible="dialog.isVisible"
        :type="dialog.type"
        @close="editClose"
        @success="editSuccess"
    />

    <!--应该用不上的-->
    <file-import
        ref="import"
        :dialog-visible="fileImport.isVisible"
        :type="fileImport.type"
        :action="fileImport.action"
        accept=".xls,.xlsx"
        @close="importClose"
        @success="importSuccess"
    />
    <el-dialog
        v-el-drag-dialog
        :close-on-click-modal="false"
        :close-on-press-escape="true"
        title="预览"
        width="80%"
        top="50px"
        :visible.sync="preview.isVisible"
    >
      <el-scrollbar>
        <div v-html="preview.context" />
      </el-scrollbar>
    </el-dialog>
  </div>
</template>

<script>
import Pagination from "@/components/Pagination";
import encStateEdit from "./edit";
import cameraApi from "@/api/Camera.js";
import elDragDialog from '@/directive/el-drag-dialog'
import FileImport from "@/components/lamp/Import"
import {downloadFile, initQueryParams} from '@/utils/commons'

export default {
  name: "EncStateManage",
  directives: {elDragDialog},
  components: {Pagination, encStateEdit, FileImport},
  filters: {},
  data() {
    return {
      dialog: {
        isVisible: false,
        type: "add"
      },
      preview: {
        isVisible: false,
        context: ''
      },
      fileImport: {
        isVisible: false,
        type: "import",
        action: `${process.env.VUE_APP_BASE_API}/authority/encState/import`
        //action: `${process.env.VUE_APP_BASE_API}/enc/encadd`                        //修改
      },
      tableKey: 0,
      queryParams: initQueryParams({
        model: {}
      }),
      selection: [],
      loading: false,
      tableData: {
        total: 0
      },
    };
  },
  computed: {},
  watch: {},
  mounted() {
    this.fetch();
  },
  methods: {
    editClose() {
      this.dialog.isVisible  = false;
    },
    editSuccess() {
      this.search();
    },
    onSelectChange(selection) {
      this.selection = selection;
    },
    search() {
      this.fetch({
        ...this.queryParams
      });
    },
    reset() {
      this.queryParams = initQueryParams({});
      this.$refs.table.clearSort();
      this.$refs.table.clearFilter();
      this.search();
    },
    exportExcelPreview() {
      if (this.queryParams.timeRange) {
        this.queryParams.extra.createTime_st = this.queryParams.timeRange[0];
        this.queryParams.extra.createTime_ed = this.queryParams.timeRange[1];
      }
      this.queryParams.extra.fileName = '导出参数数据';
      cameraApi.preview(this.queryParams).then(response => {
        const res = response.data;
        this.preview.isVisible = true;
        this.preview.context = res.data;
      });
    },
    exportExcel() {
      if (this.queryParams.timeRange) {
        this.queryParams.extra.createTime_st = this.queryParams.timeRange[0];
        this.queryParams.extra.createTime_ed = this.queryParams.timeRange[1];
      }
      this.queryParams.extra.fileName = '导出参数数据';
      cameraApi.export(this.queryParams).then(response => {
        downloadFile(response);
      });
    },
    importExcel() {
      this.fileImport.type = "upload";
      this.fileImport.isVisible = true;
      this.$refs.import.setModel(false);
    },
    importSuccess() {
      this.search();
    },
    importClose() {
      this.fileImport.isVisible = false;
    },
    singleDelete(row) {
      this.$refs.table.clearSelection();
      this.$refs.table.toggleRowSelection(row, true);
      this.batchDelete();
    },
    batchDelete() {
      if (!this.selection.length) {
        this.$message({
          message: this.$t("tips.noDataSelected"),
          type: "warning"
        });
        return;
      }
      this.$confirm(this.$t("tips.confirmDelete"), this.$t("common.tips"), {
        confirmButtonText: this.$t("common.confirm"),
        cancelButtonText: this.$t("common.cancel"),
        type: "warning"
      })
          .then(() => {
            const ids = this.selection.map(u => u.id);
            this.delete(ids);
          })
          .catch(() => {
            this.clearSelections();
          });
    },
    clearSelections() {
      this.$refs.table.clearSelection();
    },
    delete(ids) {
      cameraApi.delete(ids).then(response => {
        const res = response.data;
        if (res.isSuccess) {
          this.$message({
            message: this.$t("tips.deleteSuccess"),
            type: "success"
          });
        }
        this.search();
      });
    },
    add() {
      this.dialog.type = "add";
      this.dialog.isVisible = true;
      this.$refs.edit.setencState(false);
    },
    copy(row) {
      row.id = null;
      this.$refs.edit.setencState(row);
      this.dialog.type = "copy";
      this.dialog.isVisible = true;
    },
    edit(row) {
      this.$refs.edit.setencState(row);
      this.dialog.type = "edit";
      this.dialog.isVisible = true;
    },
    fetch(params = {}) {
      this.loading = true;
      if (this.queryParams.timeRange) {
        this.queryParams.extra.createTime_st = this.queryParams.timeRange[0];
        this.queryParams.extra.createTime_ed = this.queryParams.timeRange[1];
      }

      this.queryParams.current = params.current ? params.current : this.queryParams.current;
      this.queryParams.size = params.size ? params.size : this.queryParams.size;


      cameraApi.page(this.queryParams).then(response => {
        const res = response.data;
        if (res.isSuccess) {
          this.tableData = res.data;
        }
      }).finally(() => this.loading = false);
    },
    sortChange(val) {
      this.queryParams.sort = val.prop;
      this.queryParams.order = val.order;
      if (this.queryParams.sort) {
        this.search();
      }
    },
    filterChange(filters) {
      for (const key in filters) {
        if (key.includes('.')) {
          const val = {};
          val[key.split('.')[1]] = filters[key][0];
          this.queryParams.model[key.split('.')[0]] = val;
        } else {
          this.queryParams.model[key] = filters[key][0]
        }
      }
      this.search()
    },
    cellClick (row, column) {
      if (column['columnKey'] === "operation") {
        return;
      }
      let flag = false;
      this.selection.forEach((item) => {
        if (item.id === row.id) {
          flag = true;
          this.$refs.table.toggleRowSelection(row);
        }
      })

      if (!flag) {
        this.$refs.table.toggleRowSelection(row, true);
      }
    }
  }
};
</script>
<style lang="scss" scoped></style>
