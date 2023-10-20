<template>
  <div class="app-container">
    <div class="filter-container">

      <el-input
        :placeholder="$t('table.task.ecnSelection')"
        class="filter-item search-item"
        v-model="queryParams.model.ecnSelection"
        placeholder='推理机选择'
      />
      <el-input
        :placeholder="$t('table.task.dataUrl')"
        class="filter-item search-item"
        v-model="queryParams.model.dataUrl"
        placeholder='推理数据url'
      />
      <el-input
        :placeholder="$t('table.task.modelSelection')"
        class="filter-item search-item"
        v-model="queryParams.model.modelSelection"
        placeholder='模型选择'
      />

      <el-date-picker
        :range-separator="null"
        class="filter-item search-item date-range-item"
        end-placeholder="结束日期"
        format="yyyy-MM-dd HH:mm:ss"
        start-placeholder="开始日期"
        type="daterange"
        v-model="queryParams.timeRange"
        value-format="yyyy-MM-dd HH:mm:ss"
      />

      <el-button @click="search" class="filter-item" plain type="primary">
        {{ $t("table.search") }}
      </el-button>
      
      <el-button @click="reset" class="filter-item" plain type="warning">
        {{ $t("table.reset") }}
      </el-button>

      <el-button @click="add" class="filter-item" plain type="danger">
        {{ $t("table.add") }}
      </el-button>

    

      
      <el-dropdown class="filter-item" trigger="click">
        <el-button>
          {{ $t("table.more") }}<i class="el-icon-arrow-down el-icon--right"/>
        </el-button>
        <el-dropdown-menu slot="dropdown">
          <el-dropdown-item @click.native="batchDelete">
            {{ $t("table.delete") }}
          </el-dropdown-item>
          <el-dropdown-item @click.native="exportExcel" v-has-permission="['task:state:export']">
            {{ $t("table.export") }}
          </el-dropdown-item>
          <el-dropdown-item @click.native="exportExcelPreview" v-has-permission="['task:state:export']">
            {{ $t("table.exportPreview") }}
          </el-dropdown-item>
          <el-dropdown-item @click.native="importExcel" v-has-permission="['task:state:import']">
            {{ $t("table.import") }}
          </el-dropdown-item>
        </el-dropdown-menu>
      </el-dropdown>
    </div>

    <el-table
      :data="tableData.records"
      :key="tableKey"
      @filter-change="filterChange"
      @selection-change="onSelectChange"
      @sort-change="sortChange"
      @cell-click="cellClick"
      border fit row-key="id"
      ref="table"
      style="width: 100%;"
      v-loading="loading">
      <el-table-column align="center" type="selection" width="40px" :reserve-selection="true"/>

      <el-table-column :label="$t('table.task.createBy')" :show-overflow-tooltip="true" align="center"
                       prop="createBy" width="" label='创建人'>
        <template slot-scope="scope">
          <span>{{ scope.row.createBy }}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.createTime')" :show-overflow-tooltip="true" align="center"
                       prop="createTime" width="" label='创建时间'>
        <template slot-scope="scope">
          <span>{{ scope.row.createTime }}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.dataUrl')" :show-overflow-tooltip="true" align="center"
                       prop="dataUrl" width="" label='推理数据url'>
        <template slot-scope="scope">
          <span>{{ scope.row.dataUrl}}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.ecnSelection')" :show-overflow-tooltip="true" align="center"
                       prop="ecnSelection" width="" label='推理机选择'>
        <template slot-scope="scope">
          <span>{{ scope.row.ecnSelection}}</span>
        </template>
      </el-table-column>
     
      <el-table-column :label="$t('table.task.endTime')" :show-overflow-tooltip="true" align="center"
                       prop="endTime" width="" label='结束时间'>
        <template slot-scope="scope">
          <span>{{ scope.row.endTime}}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.modelParameter')" :show-overflow-tooltip="true" align="center"
                       prop="modelParameter" width="" label='模型参数'>
        <template slot-scope="scope">
          <span>{{ scope.row.modelParameter}}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.modelSelection')" :show-overflow-tooltip="true" align="center"
                       prop="modelSelection" width="" label='模型选择'>
        <template slot-scope="scope">
          <span>{{ scope.row.modelSelection}}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.startTime')" :show-overflow-tooltip="true" align="center"
                       prop="startTime" width="" label='开始时间'>
        <template slot-scope="scope">
          <span>{{ scope.row.startTime}}</span>
        </template>
      </el-table-column>

      <el-table-column :label="$t('table.task.taskName')" :show-overflow-tooltip="true" align="center"
                       prop="taskName" width="" label='任务名称'>
        <template slot-scope="scope">
          <span>{{ scope.row.taskName}}</span>
        </template>
      </el-table-column>

      <el-table-column
        :label="$t('table.createTime')"
        align="center"
        prop="createTime"
        sortable="custom"
        width="170px">
        <template slot-scope="scope">
          <span>{{ scope.row.createTime }}</span>
        </template>
      </el-table-column>
      <el-table-column
        :label="$t('table.operation')" column-key="operation" align="center" class-name="small-padding fixed-width" width="100px">
        <template slot-scope="{ row }">
          <i @click="copy(row)" class="el-icon-copy-document table-operation" :title="$t('common.delete')"
             style="color: #2db7f5;"/>
          <i @click="edit(row)" class="el-icon-edit table-operation" :title="$t('common.delete')"
             style="color: #2db7f5;" />
          <i @click="singleDelete(row)" class="el-icon-delete table-operation" :title="$t('common.delete')"
             style="color: #f50;" />

             <i @click="arrange(row)" class="el-icon-arrange table-operation" :title="$t('common.arrange')"
             style="color: #f50;" />

             <i
            @click="singleDownload(row)"
            class="el-icon-download table-operation"
            style="color: #f50;"
            
          />
         
        </template>
      </el-table-column>
    </el-table>
    <pagination
      :limit.sync="queryParams.size"
      :page.sync="queryParams.current"
      :total="Number(tableData.total)"
      @pagination="fetch"
      v-show="tableData.total > 0"/>
    <task-edit
      :dialog-visible="dialog.isVisible"
      :type="dialog.type"
      @close="editClose"
      @success="editSuccess"
      ref="edit"/>
    <file-import
      :dialog-visible="fileImport.isVisible"
      :type="fileImport.type"
      :action="fileImport.action" accept=".xls,.xlsx"
      @close="importClose"
      @success="importSuccess"
      ref="import"
    />
    <el-dialog
      :close-on-click-modal="false"
      :close-on-press-escape="true"
      title="预览"
      width="80%"
      top="50px"
      :visible.sync="preview.isVisible"
      v-el-drag-dialog>
      <el-scrollbar>
        <div v-html="preview.context"></div>
      </el-scrollbar>
    </el-dialog>
  </div>
</template>

<script>
  import Pagination from "@/components/Pagination";
  import taskEdit from "./edit";
  import taskApi from "@/api/task.js";
  import elDragDialog from '@/directive/el-drag-dialog'
  import FileImport from "@/components/lamp/Import"
  import {downloadFile, initDicts, initEnums, initQueryParams} from '@/utils/commons'

  export default {
    name: "taskManage",
    directives: {elDragDialog},
    components: {Pagination, taskEdit, FileImport},
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
          action: `${process.env.VUE_APP_BASE_API}/authority/task/import`
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
        this.dialog.isVisible = false;
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
        taskApi.preview(this.queryParams).then(response => {
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
        taskApi.export(this.queryParams).then(response => {
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
        taskApi.delete(ids).then(response => {
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
        this.$refs.edit.settask(false);
      },
      copy(row) {
        row.id = null;
        this.$refs.edit.settask(row);
        this.dialog.type = "copy";
        this.dialog.isVisible = true;
      },
      edit(row) {
        this.$refs.edit.settask(row);
        this.dialog.type = "edit";
        this.dialog.isVisible = true;
      },

      arrange(row){
        this.$refs.edit.settask(row);
        this.dialog.type = "arrange";
        this.dialog.isVisible = true;
      },

      download(ids) {
      attachmentApi.download(ids).then(response => {
        downloadFile(response);
        this.clearSelections();
      });
    },

      fetch(params = {}) {
        this.loading = true;
        if (this.queryParams.timeRange) {
          this.queryParams.extra.createTime_st = this.queryParams.timeRange[0];
          this.queryParams.extra.createTime_ed = this.queryParams.timeRange[1];
        }

        this.queryParams.current = params.current ? params.current : this.queryParams.current;
        this.queryParams.size = params.size ? params.size : this.queryParams.size;


        taskApi.page(this.queryParams).then(response => {
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
